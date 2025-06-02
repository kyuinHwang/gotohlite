import sys,os
from ctypes import *
BASE_DIR = os.path.dirname(os.path.abspath(__file__))
library_100bp   = BASE_DIR + '/libs/ver_100bp/NW_library.so'
library_1000bp  = BASE_DIR + '/libs/ver_1000bp/NW_library.so'
library_10000bp = BASE_DIR + '/libs/ver_10000bp/NW_library.so'

nw_library_100bp = CDLL(library_100bp)
global_alignment_100bp = nw_library_100bp.global_alignment
global_alignment_100bp.argtypes = [c_char_p,c_char_p,c_int,c_int,c_int,c_int,c_int,c_int]
global_alignment_100bp.restype = c_void_p
free_memory_100bp = nw_library_100bp.free_memory
free_memory_100bp.argtypes = c_void_p,
free_memory_100bp.restype = None

nw_library_1000bp = CDLL(library_1000bp)
global_alignment_1000bp = nw_library_1000bp.global_alignment
global_alignment_1000bp.argtypes = [c_char_p,c_char_p,c_int,c_int,c_int,c_int,c_int,c_int]
global_alignment_1000bp.restype = c_void_p
free_memory_1000bp = nw_library_1000bp.free_memory
free_memory_1000bp.argtypes = c_void_p,
free_memory_1000bp.restype = None

nw_library_10000bp = CDLL(library_10000bp)
global_alignment_10000bp = nw_library_10000bp.global_alignment
global_alignment_10000bp.argtypes = [c_char_p,c_char_p,c_int,c_int,c_int,c_int,c_int,c_int]
global_alignment_10000bp.restype = c_void_p
free_memory_10000bp = nw_library_10000bp.free_memory
free_memory_10000bp.argtypes = c_void_p,
free_memory_10000bp.restype = None


## matrix = EDNAFULL x2 
#          ! because of ext penalty 0.5 is float as standard,
#           I use 2 fold EDNAFULL for integer type data interpretation
# default : global_alignment_100bp(seq1,seq2,gopen,gext,right_end_open,right_end_ext,left_end_open,left_end_ext)
## Add encode() for input text, decode() for output text : in 2025.05 for python 3.*
def cglobal_alignment(seq1,seq2,gopen=-20,gext=-1,right_end_open=0,right_end_ext=0,left_end_open=0,left_end_ext=0):
    maxLen = max(len(seq1),len(seq2))
    seq1R, seq2R = ''.join(seq1)[::-1].encode(), ''.join(seq2)[::-1].encode()
    if maxLen < 100:
        str_return = global_alignment_100bp(seq1R,seq2R,gopen,gext,\
                           left_end_open,left_end_ext, \
                           right_end_open,right_end_ext)
        a_seq1,a_seq2 = cast(str_return,c_char_p).value.decode().split('_')
        free_memory_100bp(str_return)
    elif maxLen < 1000:
        str_return = global_alignment_1000bp(seq1R,seq2R,gopen,gext,\
                           left_end_open,left_end_ext, \
                           right_end_open,right_end_ext)
        a_seq1,a_seq2 = cast(str_return,c_char_p).value.decode().split('_')
        free_memory_1000bp(str_return)
    elif maxLen < 10000:
        str_return = global_alignment_10000bp(seq1R,seq2R,gopen,gext,\
                           left_end_open,left_end_ext, \
                           right_end_open,right_end_ext)
        a_seq1,a_seq2 = cast(str_return,c_char_p).value.decode().split('_')
        free_memory_10000bp(str_return)
    else:
        raise ValueError("Length of sequence is over our limitation")
    return a_seq1,a_seq2
