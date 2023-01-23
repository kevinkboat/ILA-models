import numpy as np
import sys

if len(sys.argv) != 3:
  print("Usage: python input_generator.py [ int8 | int16 | fp16 ] output_file_path")
  exit

dtype = sys.argv[1]
file_out = sys.argv[2]

NUM_KERNEL_ELEM = 64
NUM_MAC_CELLS = 16
NUM_FEATURE_KERNELS = 5

wt_kernels = None
wt_kernels_shape = (NUM_MAC_CELLS, NUM_KERNEL_ELEM)
ft_kernels = None
ft_kernels_shape = (NUM_FEATURE_KERNELS, NUM_KERNEL_ELEM)
default_val = 0

print(f"Generating {dtype} values")
if dtype == "int8":
  largest_val = 2**4
  wt_kernels = np.random.randint(largest_val, size=wt_kernels_shape)
  ft_kernels  = np.random.randint(largest_val, size=ft_kernels_shape)
elif dtype == "int16":
  largest_val = 2**8
  wt_kernels = np.random.randint(largest_val, size=wt_kernels_shape)
  ft_kernels  = np.random.randint(largest_val, size=ft_kernels_shape)
elif dtype == "fp16":
  default_val = np.float16(0)
  rand_exp = 2 ** (np.random.randint(7))
  wt_kernels = np.float16(np.random.rand(*wt_kernels_shape) * rand_exp)
  ft_kernels  = np.float16(np.random.rand(*ft_kernels_shape) * rand_exp)
else:
    print("Invalid datatype given. Valid options are int8, int16, and fp16")
    exit

if (wt_kernels is None) or (ft_kernels is None):
  print("Error: Inputs were not generated. Check code")
  exit 

print("Weight kernels")
for i in range(NUM_MAC_CELLS):
    for j in range(NUM_KERNEL_ELEM):
        print(f'\"cmac_csc2cmac_wt_{i}_{j}\": {wt_kernels[i][j]},')
print()

# print("Feature kernels")
for i in range(NUM_FEATURE_KERNELS):
    print (f"Feature {i}")
    for j in range(NUM_KERNEL_ELEM):
        print(f'\"cmac_csc2cmac_ft_{j}\": {ft_kernels[i][j]},')  
    print()

res = ft_kernels @ np.transpose(wt_kernels)
# print(res)

first_line = "0 " + (15 * f'{default_val} ') + "\n"
with open(file_out, "w") as file1:
    file1.write(first_line)
    for i in range(NUM_FEATURE_KERNELS):
        file1.write(str(i+1) + " ")
        for j in range(NUM_MAC_CELLS):
            file1.write(str(res[i][j]) + " ")  
        file1.write("\n")
