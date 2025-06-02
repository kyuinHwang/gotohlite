## Why gotohlite?

**gotohlite** is a memory-efficient, C-based global alignment implementation (Gotoh-style), optimized for lightweight usage in Python via `ctypes`.

### Key Features

- 🧠 **Ultra-light memory usage**
  - Uses 1D arrays instead of full 2D dynamic programming matrices.
  - A single 2D traceback matrix is used, where directions (match, gap-open, gap-extension) are compactly encoded using unique prime numbers — minimizing memory usage while preserving backtrack fidelity.

- 🛠️ **Easy to use**
  - Supports affine gap penalties (open/extension) and end gap penalties (left/right).
  - Fast C implementation combined with a convenient Python wrapper via `ctypes`.

## Installation
This pipeline requires Python 3.10 or higher.
No additional Python packages are strictly required, as the pipeline mainly uses standard libraries.

Clone the repository:

```bash
git clone https://github.com/kyuinHwang/gotohlite.git
cd gotohlite
```

### 🛠️ Build Environment (for included .so binaries)
The included shared libraries (.so) were compiled under the following environment:

OS: Ubuntu 22.10
GCC: 10.3.0
glibc: 2.32
Architecture: x86_64

Each version (ver100bp, ver1000bp, ver10000bp) contains:

C source file (.c)
Precompiled object file (.o)
Shared library (.so)
Shell script for compilation (compile.sh)

💡 If the precompiled .so files are incompatible with your system, please refer to the included compile.sh script in each directory to rebuild.

## Usage

### Environment Setup
1. Add gotohlite to your Python path

If you cloned gotohlite somewhere outside your working directory, you can add it to PYTHONPATH like this:

```python
import sys
sys.path.append("/path/to/gotohlite")  # Replace with actual path
```

2. Alternative: Set PYTHONPATH permanently (optional)

You can also export PYTHONPATH in your shell profile for convenience:
```bash
export PYTHONPATH=$PYTHONPATH:/absolute/path/to/gotohlite
```

### Running Examples

```python
from gotohlite import cglobal_alignment

aligned1, aligned2 = cglobal_alignment(
    "ACGTTAG", "ACGGTAG",
    gopen=-20, gext=-1,
    left_end_open=0, left_end_ext=0,
    right_end_open=0, right_end_ext=0
)
print(aligned1)
print(aligned2)
```

## License

This repository is released under the MIT License.

## Contact
If you encounter a problem or have a question, please open an issue on this repository:
👉 [Submit an issue](https://github.com/kyuinHwang/gotohlite/issues)

For direct inquiries, you may contact the maintainer at: rbdls77@gmail.com
