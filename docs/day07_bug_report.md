# Day 7 — Debugging Checkpoint

This checkpoint focused on reproducing bugs, gathering runtime evidence, identifying root causes, applying minimal fixes, and connecting each bug to regression coverage.

## Bug 1 — NULL Pointer Propagation

### Symptom

The program terminated before printing the expected value.

### Reproduction

`main()` initialized a pointer to `NULL` and passed it through multiple function calls:

```c
uint32_t *ptr = NULL;
process_data(ptr);
```

The pointer eventually reached:

```c
*value = 42U;
```

### Debugging Evidence

GDB showed:

```text
set_value(value = 0x0)
```

The backtrace showed the call chain:

```text
main()
  -> process_data()
      -> set_value()
```

The NULL pointer originated in `main()` and was propagated through the call chain.

### Root Cause

No valid `uint32_t` object existed for the pointer to reference.

Dereferencing the NULL pointer caused undefined behavior.

### Fix

Create a real object and pass its address:

```c
uint32_t value = 0U;

process_data(&value);
```

### Regression Principle

Public APIs that accept pointers should have clear contracts about whether NULL is permitted.

Existing project tests already exercise NULL-pointer rejection in modules such as `pointer_utils` and `adc_conversion`.

---

## Bug 2 — Off-by-One Array Access

### Symptom

The expected sample sum was:

```text
1000
```

but the program produced an incorrect value.

### Faulty Code

```c
for (size_t i = 0U; i <= count; i++)
{
    total += samples[i];
}
```

### Root Cause

For four elements, valid indexes are:

```text
0, 1, 2, 3
```

The condition:

```c
i <= count
```

also accesses:

```c
samples[4]
```

which is outside the array bounds.

This causes undefined behavior.

### Fix

Use:

```c
for (size_t i = 0U; i < count; i++)
```

### Regression Principle

Boundary tests should include exact minimum, maximum, and length-related cases.

The project's bounded sample-processing tests verify the expected result for a known array and exercise zero-length and invalid-pointer cases.

---

## Bug 3 — Tagged Union Mismatch

### Symptom

The program printed:

```text
Error: 3
```

even though the payload had been written through the button member.

### Faulty Code

```c
event.type = EVENT_ERROR;
event.payload.button_id = 3U;
```

### Root Cause

The enum tag and the selected union member did not agree.

The tag indicated:

```text
EVENT_ERROR
```

while the code wrote:

```text
payload.button_id
```

Union members share the same storage, so the bytes were later interpreted as `error_code`.

### Fix

Keep the tag and payload consistent:

```c
event.type = EVENT_ERROR;
event.payload.error_code = 3U;
```

### Regression Principle

Tagged unions should preferably be created through APIs that establish the tag and payload together.

The project's event constructor tests verify:

```text
EVENT_SENSOR -> payload.sensor
EVENT_BUTTON -> payload.button_id
EVENT_ERROR  -> payload.error_code
```

---

## Debugging Workflow

The debugging process used during this checkpoint was:

```text
Observe symptom
    ↓
Reproduce consistently
    ↓
Form a hypothesis
    ↓
Collect evidence
    ↓
Identify root cause
    ↓
Apply the smallest correct fix
    ↓
Verify behavior
    ↓
Maintain regression coverage
```

## GDB Commands Practiced

```text
break       set a breakpoint
run         start the program
print       inspect expressions and variables
next        execute the current line
backtrace   inspect the call chain
quit        leave GDB
```

The NULL-pointer bug was inspected directly with GDB and its origin was identified using a backtrace.

## Key Lessons

- The line where a program fails may only be the symptom location.
- Runtime evidence is more reliable than random code changes.
- NULL-pointer validity is an API and ownership question.
- Array bounds must use valid indexes only.
- C strings require null termination, but ordinary arrays do not.
- Tagged-union discriminators must agree with the active payload.
- Code can compile with no warnings and still contain serious logical bugs.
- A fix should address the root cause rather than merely hiding the symptom.

