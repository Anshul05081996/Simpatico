#ifndef AUTO_CORR_STAGE_TEST_H
#define AUTO_CORR_STAGE_TEST_H

#include <util/archives/MemoryOArchive.h>
#include <util/archives/MemoryIArchive.h>
#include <util/random/Random.h>
#include <util/random/Ar1Process.h>
#include <util/space/Vector.h>
#include <util/space/Tensor.h>
#include <util/containers/DArray.h>
#include <util/containers/FArray.h>
#include <util/accumulators/AutoCorrStage.h>     // template 
#include <util/accumulators/Average.h>

#include <iostream>
#include <fstream>
#include <string>

using namespace Util;

class AutoCorrStageTest 
{

public:

   AutoCorrStageTest()
    : verbose_(2)
   {}

   void setUp(const char* functionName)
   { 
      std::cout << std::string(functionName) << " :" << std::endl << std::endl;
      std::ifstream file("in/Random");
      random().readParam(file);
   }

   void tearDown()
   { 
      std::cout << "----------------------------------------------------" 
                << std::endl << std::endl;
   }


   void testAutoCorrDouble() 
   {
      setUp("testAutoCorrDouble");

      AutoCorrStage<double, double> autocorr;
      Average average;
      //autocorr.setBufferCapacity(100);
      //average.setNSamplePerBlock(1);

      Ar1Process process(random_);
      double tau = 10.0;
      process.init(tau);

      int    nSample = 1000000;
      double x;
      for (int i=0; i < nSample; i++) {
         x = process();
         autocorr.sample(x);
         //average.sample(x);
      }
      autocorr.output(std::cout);
      //average.output(std::cout);
      tearDown();
   }

   void testAutoCorrVector() 
   {
      setUp("testAutoVector");

      AutoCorrStage<Vector, double> autocorr;
      //autocorr.setBufferCapacity(100);

      Ar1Process process0(random_);
      Ar1Process process1(random_);
      Ar1Process process2(random_);
      double tau = 10.0;
      process0.init(tau);
      process1.init(tau);
      process2.init(tau);

      int    nSample =  100000;
      Vector x;
      for (int i=0; i < nSample; i++) {
         x[0] = process0();
         x[1] = process1();
         x[2] = process2();
         autocorr.sample(x);
      }
      autocorr.output(std::cout);

      tearDown();
   }

   #if 0
   void testAutoCorrSerialize() 
   {
      setUp("testAutoCorrSerialize");

      AutoCorrStage<double, double> autocorr;
      Average average;
      autocorr.setParam(100);
      average.setNSamplePerBlock(1);

      Ar1Process process(random_);
      double tau = 10.0;
      process.init(tau);

      int    nSample = 100000;
      double x;
      for (int i=0; i < nSample; i++) {
         x = process();
         autocorr.sample(x);
         average.sample(x);
      }

      MemoryOArchive u;
      MemoryIArchive v;
      u.allocate(autocorr.packedSize());
      AutoCorrStage<double, double> clone;
      u << autocorr;
      v = u;
      v >> clone;

      clone.output(std::cout);
      tearDown();
   }
   #endif

   Random& random() 
   { return random_; }

private:

   Random random_;
   int    verbose_;

};

int main()
{
   AutoCorrStageTest test;

   test.testAutoCorrDouble();
   //test.testAutoCorrVector();
   //test.testAutoCorrSerialize();
}

#endif
