# Contributing

## Adding a New Algorithm

1. **Create the algorithm file** in the appropriate category folder:
   - `Graph Algorithms/`, `Tree Algorithms/`, `Range Queries/`, `String Algorithms/`, `Number Theory/`, or `Common Techniques/`
   - Name it `AlgorithmName.cpp` using CamelCase.

2. **File requirements** — every algorithm file must be self-contained:
   - Include only the standard headers it needs (e.g. `<vector>`, `<queue>`).
   - Use explicit C++ types (`long long`, `int`) — no macros or typedefs from an external template.
   - No `main()` function, no `using namespace std;`, no boilerplate.
   - Start with a comment block: algorithm name, time complexity, brief usage note.

3. **Write a test file** at `tests/test_algorithmname.cpp`:
   - Include `"common.h"` and your algorithm file.
   - Cover at least two distinct cases (typical input + edge case).
   - Use `ASSERT_EQ`, `ASSERT_TRUE`, `ASSERT_FALSE`, and end with `TEST_PASS()`.
   - See any existing test for the pattern.

4. **Verify locally** before pushing:
   ```
   make -C tests run
   ```
   All tests must pass.

5. **Update `README.md`** — add a row to the appropriate table with the algorithm name, complexity, and description.

## Code Style

- Function and struct names: `CamelCase` for types, `camelCase` or `snake_case` for functions.
- Internal helper functions: prefix with `_` (e.g. `_dfs`).
- No comments that restate what the code already says. Only document non-obvious constraints or invariants.
