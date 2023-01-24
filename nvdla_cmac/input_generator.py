import numpy as np
import sys

NUM_KERNEL_ELEM = 64
NUM_MAC_CELLS = 16


def generateAndStoreInputs(dtype: str, num_ft_kernels: int, instr_file:str):
    print(f"Generating {dtype} values")
    
    wt_kernels = None
    ft_kernels = None
    wt_kernels_shape = (NUM_MAC_CELLS, NUM_KERNEL_ELEM)
    ft_kernels_shape = (num_ft_kernels, NUM_KERNEL_ELEM)

    if dtype == "int8":
        largest_val = 2**4
        wt_kernels = np.int8(np.random.randint(largest_val, size=wt_kernels_shape))
        ft_kernels  = np.int8(np.random.randint(largest_val, size=ft_kernels_shape))
    elif dtype == "int16":
        largest_val = 2**8
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

    prologue = '''
    {
    "program fragment": [
        {
            "instr No.": 0,
            "cmac_csb2cmac_data": 1,
            "cmac_csb2cmac_addr": "0x0008",
            "cmac_csb2cmac_write": 1,
            "cmac_csb2cmac_vld": 1
        }
    '''

    epilogue = """
        ]
    }
    """

    with open(instr_file, "w") as file1:
        file1.write(prologue)
                
        for k in range(len(ft_kernels)):
            file1.write("\t\t,{\n")
            tabs = "\t\t\t"
            file1.write(tabs + f"\"instr No.\": {k + 1}, \n")
            file1.write(tabs + f"\"cmac_csc2cmac_vld\": true, \n")
            file1.write(tabs + f"\"cmac_csc2cmac_sending_last_batch\": {str(k == num_ft_kernels - 1).lower()}, \n")

            for i in range(NUM_MAC_CELLS):
                for j in range(NUM_KERNEL_ELEM):
                    file1.write(tabs + f'\"cmac_csc2cmac_wt_{i}_{j}\": {wt_kernels[i][j]}, \n')
            for i in range(NUM_KERNEL_ELEM-1):
                file1.write(tabs + f'\"cmac_csc2cmac_ft_{i}\": {ft_kernels[k][i]}, \n')  
            file1.write(tabs + f'\"cmac_csc2cmac_ft_{NUM_KERNEL_ELEM -1}\": {ft_kernels[k][NUM_KERNEL_ELEM-1]} \n')  
            file1.write("\t\t}\n")
        
        
        file1.write(epilogue + "\n")
    return wt_kernels, ft_kernels


def generateAndStoreSolution(dtype: str, wt_kernels: np.ndarray, ft_kernels:np.ndarray, solution_file:str):
    print(f"Storing solutions in {solution_file}")
    sol = ft_kernels @ np.transpose(wt_kernels)
    
    default_val = 0
    if dtype == "fp16": default_val = np.float16(0)

    with open(solution_file, "w") as file1:
        file1.write("0 " + (16 * f'{default_val} ') + "\n")
        for i in range(len(sol)):
            file1.write(str(i+1) + " ")
            for j in range(NUM_MAC_CELLS):
                file1.write(str(sol[i][j]) + " ")  
            file1.write("\n")


def main():
    if len(sys.argv) != 5:
        print("Usage: python input_generator.py [ int8 | int16 | fp16 ] num_ft_kernels output_instr_path output_solution_path")
        exit
    
    _, dtype, num_ft_kernels, instr_file, sol_file = sys.argv
    num_ft_kernels = int(num_ft_kernels)
  
    wt_kernels, ft_kernels = generateAndStoreInputs(dtype, num_ft_kernels, instr_file)
    generateAndStoreSolution(dtype, wt_kernels, ft_kernels, sol_file)


# generate random inputs and store in user specified file along with results - dtype feature_no. instr.out 
# take in input file and generate output - dtype feature_no

if __name__ == "__main__":
    main()
