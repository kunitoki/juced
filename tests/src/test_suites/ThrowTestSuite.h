/*
 ==============================================================================

 This file is part of the JUCETICE project - Copyright 2007 by Lucio Asnaghi.

 JUCETICE is based around the JUCE library - "Jules' Utility Class Extensions"
 Copyright 2007 by Julian Storer.

 ------------------------------------------------------------------------------

 JUCE and JUCETICE can be redistributed and/or modified under the terms of
 the GNU Lesser General Public License, as published by the Free Software
 Foundation; either version 2 of the License, or (at your option) any later
 version.

 JUCE and JUCETICE are distributed in the hope that they will be useful,
 but WITHOUT ANY WARRANTY; without even the implied warranty of
 MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 GNU General Public License for more details.

 You should have received a copy of the GNU Lesser General Public License
 along with JUCE and JUCETICE; if not, visit www.gnu.org/licenses or write to
 Free Software Foundation, Inc., 59 Temple Place, Suite 330,
 Boston, MA 02111-1307 USA

 ==============================================================================
*/


class ThrowTestSuite : public Test::Suite
{
public:
	ThrowTestSuite()
	{
		TEST_ADD(ThrowTestSuite::success)
		TEST_ADD(ThrowTestSuite::test_throw)
	}
	
private:
	void success() {}
	
	void test_throw()
	{
		// Will fail since the none of the functions throws anything
		//
		TEST_THROWS_MSG(func(), int, "func() does not throw, expected int exception")
		TEST_THROWS_MSG(func_no_throw(), int, "func_no_throw() does not throw, expected int exception")
		TEST_THROWS_ANYTHING_MSG(func(), "func() does not throw, expected any exception")
		TEST_THROWS_ANYTHING_MSG(func_no_throw(), "func_no_throw() does not throw, expected any exception")
		
		// Will succeed since none of the functions throws anything
		//
		TEST_THROWS_NOTHING(func())
		TEST_THROWS_NOTHING(func_no_throw())
		
		// Will succeed since func_throw_int() throws an int
		//
		TEST_THROWS(func_throw_int(), int)
		TEST_THROWS_ANYTHING(func_throw_int())
		
		// Will fail since func_throw_int() throws an int (not a float)
		//
		TEST_THROWS_MSG(func_throw_int(), float, "func_throw_int() throws an int, expected a float exception")
		TEST_THROWS_NOTHING_MSG(func_throw_int(), "func_throw_int() throws an int, expected no exception at all")
	}
	
	void func() {}
	void func_no_throw() throw() {}
	void func_throw_int() throw(int) { throw 13; }
};


