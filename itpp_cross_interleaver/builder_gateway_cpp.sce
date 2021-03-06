// This file is released under the 3-clause BSD license. See COPYING-BSD.

function builder_gw_cpp()
    WITHOUT_AUTO_PUTLHSVAR = %t;
    tbx_build_gateway("skeleton_cpp", ..
    ["itpp_cross_interleave","itpp_cross_interleaver"], ..
    ["itpp_cross_interleaver.cpp"], ..
    get_absolute_file_path("builder_gateway_cpp.sce"), [], "-litpp");

endfunction

builder_gw_cpp();
clear builder_gw_cpp; // remove builder_gw_cpp on stack
