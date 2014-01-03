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


class ScriptingTestSuite : public Test::Suite
{
public:

    //==============================================================================
	ScriptingTestSuite()
	{
		TEST_ADD (ScriptingTestSuite::always_fail)
		TEST_ADD (ScriptingTestSuite::shared_pointer)
		TEST_ADD (ScriptingTestSuite::return_shared_pointer)
		
		TEST_ADD (ScriptingTestSuite::scripting_string)
	}
	
private:

    //==============================================================================
	void always_fail()
	{
		// This will always fail
		// TEST_FAIL ("unconditional fail");
	}

    //==============================================================================
	void shared_pointer()
	{
	    SharedPointer<int> ptr (new int(1));
	
		TEST_ASSERT_MSG(ptr.used () == 1, "smart pointer count")
		TEST_ASSERT_MSG(*ptr == 1, "smart pointer value")
		
		{
		    SharedPointer<int> ptr2 (ptr);

		    TEST_ASSERT_MSG(ptr2.used () == 2, "smart pointer2 count")
		    TEST_ASSERT_MSG(*ptr == 1, "smart pointer2 value")
		}

        TEST_ASSERT_MSG(ptr.used () == 1, "smart pointer after assignment count")
	}

    //==============================================================================
    void return_shared_pointer ()
    {
        SharedPointer<int> ptr (return_shared_ptr (5));

		TEST_ASSERT_MSG(ptr.used () == 1, "smart pointer count")
		TEST_ASSERT_MSG(*ptr == 5, "smart pointer value")
    }

    //==============================================================================
    void scripting_string ()
    {
        const char script[] = "void main() \n"
                              "{ \n"
                              "  String s(\"12345678\"); \n" // (\"12345\");\n"
                              "  String as(12345678.0f); \n" // (\"12345\");\n"
                              "  println (s == as); \n"
//                              "  println (s); \n"
//                              "  println (s); \n"
                              "} \n\n";

        ScriptableEngine engine;
        engine.compileScript (script);
        engine.executeFunction ("main");
    }

private:

    SharedPointer<int> return_shared_ptr (int value)
    {
        return SharedPointer<int> (new int (value));
    }
};


