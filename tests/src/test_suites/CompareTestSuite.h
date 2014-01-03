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


class CompareTestSuite : public Test::Suite
{
public:

	CompareTestSuite()
	{
		TEST_ADD(CompareTestSuite::success)
		TEST_ADD(CompareTestSuite::compare)
		TEST_ADD(CompareTestSuite::delta_compare)
	}
	
private:

	void success() {}
	
	void compare()
	{
		// Will succeed since the expression evaluates to true
		//
		TEST_ASSERT(1 + 1 == 2)
		
		// Will fail since the expression evaluates to false
		//
		TEST_ASSERT(0 == 1);
	}
	
	void delta_compare()
	{
		// Will succeed since the expression evaluates to true
		//
		TEST_ASSERT_DELTA(0.5, 0.7, 0.3);
		
		// Will fail since the expression evaluates to false
		//
		TEST_ASSERT_DELTA(0.5, 0.7, 0.1);
	}
};


