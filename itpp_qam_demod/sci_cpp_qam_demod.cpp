/*----------------------------------------------------------------------------------------------------------------
Code for QAM De-Modulation
Pratik Kapoor
June 1, 2015
----------------------------------------------------------------------------------------------------------------*/

/*----------------------------------------------------------------------------------------------------------------
Example

a = [0.7071068 -0.7071068i  -0.7071068 -0.7071068i]
b = itpp_qam_demod(4,a);
b = [1 0 1 1]
----------------------------------------------------------------------------------------------------------------*/


#include <numeric>
#include <itpp/comm/modulator.h>
#include <itpp/base/vec.h>
#include <itpp/itcomm.h>
#include <itpp/itbase.h>
#include <itpp/comm/modulator.h>

using namespace itpp;
using namespace std;

extern "C"
{
	#include "api_scilab.h"
	#include "Scierror.h"
	#include "BOOL.h"
	#include <localization.h>
	#include "MALLOC.h"
	#include <itpp/base/vec.h>

	/*=================================================================*/

	int sci_cpp_qam_demod(char *fname, unsigned long fname_len)
	{
		//Error management variable
		SciErr sciErr;

		//Variable declaration
		int m=0,n=0,m1=0,n1=0,row=1,col=1;  			//Matrix Dimensions
		int i=0;
		int *piAddressVar = NULL;
		int *setm = NULL;
		
		double *inputMatrixReal = NULL; 
		double *inputMatrixImg = NULL; 	//Input-Output Matrices
		double *outputMatrix = NULL;
		double *setmMatrix = NULL;

		/*=================================================================*/
		// C function which checks the number of input/output arguments present in the calling Scilab function.
		// CheckInputArgument(pvApiCtx, minArgs, maxArgs)
		// CheckOutputArgument(pvApiCtx, minArgs, maxArgs)
		// pvApiCtx --> Scilab environment pointer
		/*=================================================================*/
		
		CheckInputArgument(pvApiCtx, 2, 2);
	    	CheckOutputArgument(pvApiCtx, 1, 1);

		/*=================================================================*/
		// This function retrieves the address of an argument in a gateway.
		// sciErr getVarAddressFromPosition(void* _pvCtx, int _iVar, int** _piAddress)
		// iVAr --> Position of the argument in the function call.
		// piAddress --> Return address of the Scilab variable.
		/*=================================================================*/
		
		sciErr = getVarAddressFromPosition(pvApiCtx, 2, &piAddressVar);
		sciErr = getVarAddressFromPosition(pvApiCtx, 1, &setm);
		
	    	if (sciErr.iErr)
	    	{
			printError(&sciErr, 0);
			return 0;
	    	}
	    	
	    	
	    	/*=================================================================*/
	    	// Getting Input Signal
		// SciErr getMatrixOfDouble(void* _pvCtx, int* _piAddress, int* _piRows, int* _piCols, double** _pdblReal)
		/*=================================================================*/
	    	sciErr = getComplexMatrixOfDouble(pvApiCtx, piAddressVar, &m, &n, &inputMatrixReal, &inputMatrixImg);
	    	sciErr = getMatrixOfDouble(pvApiCtx, setm, &m1, &n1, &setmMatrix);
	    	
	    	if (sciErr.iErr)
	    	{
			printError(&sciErr, 0);
			return 0;
	    	}
	    	
	    	//Checking if input signal is a vector
		if((m1!=1) && (n1!=1)) 
		{
			Scierror(2, _("%s: Single row or column vector expected.\n"), fname, 1);
			return 0;
		}
		
		
		//----------------------------------WORKING OF FUNCTION-------------------------//
		
		//Declaring input and output vectors for modulation
		vec inputReal, inputImg;
		bvec outputVector;
		cvec inputVector;

		//Converting input Real and imaginary matrices into vectors
		inputReal = vec(inputMatrixReal, m * n);
		inputImg = vec(inputMatrixImg, m * n);
		inputVector = itpp::to_cvec(inputReal, inputImg);
		
		/*=================================================================*/
		// virtual bvec demodulate_bits (const cVec< double > &signal) const
		// Calling the required IT++ function
		
		outputVector = QAM((int)*setmMatrix).demodulate_bits(inputVector);
		
		/*=================================================================*/
		
		int relative = log((int)*setmMatrix)/log(2);
	
		//Storing the output in a double array to be sent to scilab
		outputMatrix = (double *) malloc( sizeof(double)*m*n*relative);
		
		for(i=0; i < m*n*relative; i++)
		{
			outputMatrix[i] = outputVector(i);
		}
		
		//Creating Output Modulated Signal
		sciErr = createMatrixOfDouble(pvApiCtx, nbInputArgument(pvApiCtx) + 1, m, n*relative, outputMatrix);
 
	    	if (sciErr.iErr)
	    	{
			printError(&sciErr, 0);
			return 0;
	    	}

		free(outputMatrix); 


		//Returning output arguements to Scilab

		AssignOutputVariable(pvApiCtx, 1) = nbInputArgument(pvApiCtx) + 1;

		ReturnArguments(pvApiCtx);
	
		return 0;
	}
	
}

		
		
		
		
		
		
		
		
		
		
		
		
