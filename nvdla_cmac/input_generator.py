import numpy as np
import sys

NUM_KERNEL_ELEM = 64
NUM_MAC_CELLS = 16

def generateAndStoreInputs(dtype:str, wt_kernels_shape:tuple, ft_kernels_shape:tuple, instr_file:str):
    print(f"Generating {dtype} values")
    
    wt_kernels = None
    ft_kernels = None
    if dtype == "int8":
        largest_val = 10
        wt_kernels = np.int8(np.random.randint(largest_val, size=wt_kernels_shape))
        ft_kernels  = np.int8(np.random.randint(largest_val, size=ft_kernels_shape))
    elif dtype == "int16":
        largest_val = 100
        wt_kernels = np.int16(np.random.randint(largest_val, size=wt_kernels_shape))
        ft_kernels  = np.int16(np.random.randint(largest_val, size=ft_kernels_shape))
    elif dtype == "fp16":
        rand_exp1 = 2 ** (np.random.randint(7, size=wt_kernels_shape))
        rand_exp2 = 2 ** (np.random.randint(7, size=ft_kernels_shape))
        wt_kernels = np.float16(np.random.rand(*wt_kernels_shape) * rand_exp1)
        ft_kernels  = np.float16(np.random.rand(*ft_kernels_shape) * rand_exp2)
    else:
        print("Invalid datatype given. Valid options are int8, int16, and fp16")
        exit

    if (wt_kernels is None) or (ft_kernels is None):
        print("Error: Inputs were not generated. Check code")
        exit

    with open(instr_file, "w") as file1:
        for k in range(ft_kernels_shape[0]):
            file1.write(f'********* Input set no. {k} *********\n')

            file1.write(f'Numpy arrays: \n')
            with np.printoptions(threshold=np.inf):
                file1.write(f'wt_kernels={wt_kernels}\n')
                file1.write(f'ft_kernels={ft_kernels}\n\n')

            file1.write(f'JSON inputs: \n')
            for i in range(wt_kernels_shape[0]):
                for j in range(wt_kernels_shape[1]):
                    file1.write(f'\"cmac_csc2cmac_wt_{i}_{j}\": {wt_kernels[i][j]}, \n')

            for i in range(ft_kernels_shape[1]):
                file1.write(f'\"cmac_csc2cmac_ft_{i}\": {ft_kernels[k][i]}, \n')  
            file1.write(f'********* Input set of Output set no. {k}*********\n\n')
        
    return wt_kernels, ft_kernels


def generateAndStoreSolution(dtype: str, wt_kernels: np.ndarray, ft_kernels:np.ndarray, solution_file:str):
    print(f"Storing solutions in {solution_file}")
    sol = ft_kernels @ np.transpose(wt_kernels)
    
    dim_diff = max(0, 16 - sol.shape[1])
    print(dim_diff, sol.shape)

    sol = np.pad(sol, pad_width=((0,0),(0,dim_diff)), mode='constant', constant_values=(0))

    print(dim_diff, sol.shape, sol)
    if dtype == "int8":
        sol = np.int8(sol)
    elif dtype == "int16":
        sol = np.int16(sol)
    elif dtype == "fp16":
        sol = np.float16(sol)

    with open(solution_file, "w") as file1:
        # file1.write('sol = ft_kernels @ numpy.transpose(wt_kernels)\n\n')
        for i in range(sol.shape[0]):
            file1.write(f'Reset {i+1} \n')
            file1.write(f'consumer = {i+1} \n')
            for j in range(sol.shape[1]):
                file1.write(f'mac_{j}' + 4*' 0'+ " \n")  
            file1.write("\n")

            file1.write(f'Solution {i+1} \n')
            file1.write(f'consumer = {i+1} \n')
            for j in range(sol.shape[1]):
                file1.write(f'mac_{j} '+ str(sol[i][j]) + 3*' 0'+ " \n")  
            file1.write("\n")

                

def main():
    if len(sys.argv) != 5:
        print("Usage: python input_generator.py [ int8 | int16 | fp16 ] num_weight_kernels num_ft_kernels output_base_name")
        exit
    
    _, dtype, num_weight_kernels, num_ft_kernels, output_base_name = sys.argv
  
    instr_file = output_base_name + "_input.txt"
    sol_file = output_base_name + '_sol.txt'
    wt_kernels_shape = (int(num_weight_kernels), NUM_KERNEL_ELEM) 
    ft_kernels_shape = (int(num_ft_kernels), NUM_KERNEL_ELEM)

    wt_kernels, ft_kernels = generateAndStoreInputs(dtype, wt_kernels_shape, ft_kernels_shape, instr_file)
    generateAndStoreSolution(dtype, wt_kernels, ft_kernels, sol_file)


# generate random inputs and store in user specified file along with results - dtype feature_no. instr.out 
# take in input file and generate output - dtype feature_no

if __name__ == "__main__":
    main()
