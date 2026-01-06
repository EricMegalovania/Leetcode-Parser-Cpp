from <https://support.leetcode.com/hc/en-us/articles/32442719377939-How-to-create-test-cases-on-LeetCode>

> [!Note]
>
> ## 3.1 Basic Data Types
>
> This section covers fundamental data types like integers, booleans, characters, and strings. These are the building blocks for more complex data structures, so mastering their input format is essential for handling advanced structures.
>
> | **Type**  | **Description**                                              | **Examples**                                                 | **Notes**                                                    |
> | :-------- | :----------------------------------------------------------- | :----------------------------------------------------------- | :----------------------------------------------------------- |
> | integer   | A numerical data type that represents whole numbers without any decimal component. Typically 4 bytes (32 bits) in size. | 1. `-1`<br />2. `0`<br />3. `2147483647`                     | The range for an integer is $[-2^{31}, 2^{31}-1]$.           |
> | long      | An extended version of the integer type that can store larger numerical values. Typically 8 bytes (64 bits) in size. | 1. `-1`<br />2. `0`<br />3. `-9223372036854775808`           | The range for a long integer is $[−2^{63}, 2^{63}-1]$.       |
> | boolean   | A data type that represents one of two binary values: `true` or `false`. | 1. `true`<br />2. `false`                                    |                                                              |
> | double    | A numerical data type used to represent floating-point numbers with decimal notation. Typically 8 bytes (64 bits) in size. | 1. `245.32`<br />2. `1.0000`<br />3. `-1000000000000.2345`   | The range for a double is approximately $[−1.7 × 10^{308}, 1.7 × 10^{308}]$.<br />Avoid using commas or multiple decimal points. |
> | character | A data type that represents a single alphanumeric character, symbol, or punctuation mark. Typically 1 byte (8 bits) in size, supporting ASCII. | 1. `"a"`<br />2. `"\n"` newline<br />3. `"\\"` backslash     | Character must be within the standard ASCII range (0 to 127).<br />A character must be enclosed in double quotes (`"`). Use escape sequences (e.g., `\\` for backslash) where necessary. |
> | string    | A sequence of characters, including letters, digits, punctuation, whitespace, and other symbols. | 1. `""` empty string<br />2. `"Hello world"`<br />3. `"1337's \"world\""` | Strings must be enclosed in double quotes (`"`). Each character in the string must be within the standard ASCII range (0 to 127). |
>
> ## 3.2 Standard Data Structures
>
> LeetCode problems often involve complex data structures like Linked Lists and Binary Trees, which are pre-defined to save you time. The table below shows how to format and input these structures for your test cases.
>
> | **Type** | **Description**                                              | **Examples**                                                 | **Notes**                                                    |
> | :------- | :----------------------------------------------------------- | :----------------------------------------------------------- | :----------------------------------------------------------- |
> | Array    | A data structure that holds a sequence of elements of the same data type. | 1. `[]` Empty array.<br />2. `[1]` Single integer.<br />3. `["a","hello","world"]` 3 strings. | Arrays must contain elements of the same data type.          |
> | 2D Array | An array of arrays, where each sub-array represents a row. It can hold elements in a matrix-like structure. | 1. `[]` Empty 2D array.<br />2. `[[]]` 1 row, 0 elements.<br />3. `[[1]]` 1 row, 1 element.<br />4. `[[1,2],[3,4]]` 2x2 array.<br />5. `[[1],[2,3],[4,5,6]]` 3 rows. | 2D arrays can either have a fixed number of columns (e.g., `int[,]` in C#) or a variable number of columns (e.g., `int[][]` in C#). Always check the problem's requirements or the programming language's specifics to understand the structure. |
>
> Binary Tree
>
> - `[]`
>
>   ```text
>   Empty tree. The root is a reference to NULL (C/C++), null (Java/C#/Javascript), None (Python), or nil (Ruby).
>   ```
>
> - `[1, 2, 3]`
>
>   ```text
>        1
>       / \
>      2   3
>   ```
>
> - `[1, null, 2, 3]`
>
>   ```text
>        1
>         \
>          2
>         /
>        3
>   ```
>
> - `[5, 4, 7, 3, null, 2, null, -1, null, 9]`
>
>   ```text
>         5
>        / \
>       4   7
>      /   /
>     3   2
>    /   /
>   -1  9
>   ```

**Linked List** are not implemented yet.