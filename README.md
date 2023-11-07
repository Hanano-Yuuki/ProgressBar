# ProgressBar
a header only progress bar library for cpp

# Features
1. Track execution time with high precision
2. Provides linear execution time prediction
3. Lock-free
4. Low overhead (less than 1%)
# API
- **ProgressBar(T totalTaskNumbers=0) - Constructor**
  - Create a progressbar with given total number of tasks
- **init(int totalTaskNumbers,float precision=0)**
  - Initialize the progressbar, set the total number of tasks and update precision (default 1, ranging from 0~1)
- **setWidth(int width)**
  - Set the width of progressbar to avoid exceeding the console
- **inc(int taskNumbers=1)**
  - Submit the number of completed tasks (default 1)
- **update()**
  - Update the displayed progressbar

# TODO
1. Non-linear execution time prediction
2. Visualize execution progress