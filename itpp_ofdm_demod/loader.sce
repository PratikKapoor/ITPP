// This file is released under the 3-clause BSD license. See COPYING-BSD.
// Generated by builder.sce : Please, do not edit this file
// ----------------------------------------------------------------------------
//
libskeleton_cpp_path = get_absolute_file_path('loader.sce');
//
// ulink previous function with same name
[bOK, ilib] = c_link('libskeleton_cpp');
if bOK then
  ulink(ilib);
end
//
list_functions = [ 'itpp_ofdm_demod';
];
addinter(libskeleton_cpp_path + filesep() + 'libskeleton_cpp' + getdynlibext(), 'libskeleton_cpp', list_functions);
// remove temp. variables on stack
clear libskeleton_cpp_path;
clear bOK;
clear ilib;
clear list_functions;
// ----------------------------------------------------------------------------
