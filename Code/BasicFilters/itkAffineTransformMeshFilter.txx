/*=========================================================================

  Program:   Insight Segmentation & Registration Toolkit
  Module:    itkAffineTransformMeshFilter.txx
  Language:  C++
  Date:      $Date$
  Version:   $Revision$


  Copyright (c) 2000 National Library of Medicine
  All rights reserved.

  See COPYRIGHT.txt for copyright details.

=========================================================================*/
#include "itkAffineTransformMeshFilter.h"
#include "itkExceptionObject.h"

namespace itk
{
  
/**
 *
 */
template <class TInputMesh, class TOutputMesh>
AffineTransformMeshFilter<TInputMesh,TOutputMesh>
::AffineTransformMeshFilter()
{
}


/**
 *
 */
template <class TInputMesh, class TOutputMesh>
void 
AffineTransformMeshFilter<TInputMesh,TOutputMesh>
::PrintSelf(std::ostream& os, Indent indent)
{
  Superclass::PrintSelf(os,indent);
}


/**
 * This method causes the filter to generate its output.
 */
template <class TInputMesh, class TOutputMesh>
void 
AffineTransformMeshFilter<TInputMesh,TOutputMesh>
::GenerateData(void) 
{
  
  typedef TInputMesh::PointsContainer  InputPointsContainer;
  typedef TOutputMesh::PointsContainer OutputPointsContainer;

  typedef TInputMesh::PointsContainerPointer  InputPointsContainerPointer;
  typedef TOutputMesh::PointsContainerPointer OutputPointsContainerPointer;

  InputMeshPointer    inputMesh      =  GetInput();
  OutputMeshPointer   outputMesh     =  GetOutput();
  
  if( !inputMesh )
  {
    throw ExceptionObject();
  }

  if( !outputMesh )
  {
    throw ExceptionObject();
  }

  InputPointsContainerPointer  inPoints  = inputMesh->GetPoints();
  OutputPointsContainerPointer outPoints = outputMesh->GetPoints();

  outPoints->Reserve( inputMesh->GetNumberOfPoints() );
  outPoints->Squeeze();

  InputPointsContainer::ConstIterator  inputPoint  = inPoints->Begin();
  OutputPointsContainer::Iterator outputPoint = outPoints->Begin();

  while( inputPoint != inPoints->End() ) 
  {

    outputPoint.Value() = 
	           m_AffineTransform.Transform( inputPoint.Value() );

    ++inputPoint;
    ++outputPoint;
  }

}




} // end namespace itk
