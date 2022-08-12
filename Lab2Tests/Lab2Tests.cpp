#include "pch.h"
#include "CppUnitTest.h"


using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace Lab2Tests
{
	TEST_CLASS(Lab2Tests)
	{
	public:
		
		TEST_METHOD(Mat4MultiplicationTest)
		{
			mat_4 test_mat = {
				{51, 2, 1, 26},
				{1, 2, 1, 2},
				{12, 2, 13, 2},
				{1, 2, 1, 25},
			};
			double test_mat_flat[16];
			test_mat.flatten(test_mat_flat);

			double flat_inv[16];
			//mat_4::inverse(test_mat_flat, flat_inv);

			mat_4 test_inv_mat{flat_inv};

			const auto res = test_mat * test_inv_mat;

			Assert::IsTrue(res == mat_4::identity(), L"Matrix and its inverse are not equal to identity.");
		}

		TEST_METHOD(mat2_inverse_test)
		{
			mat_2 a = {{1, 2}, {3, 4}};
			mat_2 ai = a.inverse();

			mat_2 resa = a*ai;
			const auto test1 = resa == mat_2::identity();

			Assert::IsTrue(test1, L"result*original did not match identity of 2x2 matrix.");

			mat_2 c = { {51.0, -22.0}, {1.0/3.0, 4.0/22.0} };
			mat_2 ci = c.inverse();

			mat_2 resc = c * ci;
			const auto test2 = resc == mat_2::identity();

			Assert::IsTrue(test2, L"result*original did not match identity of 2x2 matrix.");
		}
	};
}
