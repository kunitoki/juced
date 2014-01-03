// ---
//
// $Id: mytest.cpp,v 1.5 2008/07/11 16:49:43 hartwork Exp $
//
// CppTest - A C++ Unit Testing Framework
// Copyright (c) 2003 Niklas Lundell
//
// ---
//
// This library is free software; you can redistribute it and/or
// modify it under the terms of the GNU Lesser General Public
// License as published by the Free Software Foundation; either
// version 2 of the License, or (at your option) any later version.
//
// This library is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
// Lesser General Public License for more details.
//
// You should have received a copy of the GNU Lesser General Public
// License along with this library; if not, write to the
// Free Software Foundation, Inc., 59 Temple Place - Suite 330,
// Boston, MA 02111-1307, USA.
//
// ---
//
// Test program demonstrating all assert types and output handlers.
//
// ---

#include "config.h"

#ifdef JUCETICE_USE_AMALGAMA
 #include "../../juce/juce_amalgamated.cpp"
#else
 #include "../../juce/juce.h"
#endif

#include "test_suites/ScriptingTestSuite.h"
#include "test_suites/CompareTestSuite.h"
#include "test_suites/ThrowTestSuite.h"

enum OutputType
{
	Compiler,
	Html,
	TextTerse,
	TextVerbose
};

static void usage()
{
	std::cout << "usage: mytest [MODE]\n"
	          << "where MODE may be one of:\n"
		      << "  --compiler\n"
		      << "  --html\n"
		      << "  --text-terse (default)\n"
		      << "  --text-verbose\n";
	exit(0);
}

static Test::Output* cmdline(int argc, char* argv[])
{
	if (argc > 2)
		usage(); // will not return
	
	Test::Output* output = 0;
	
	if (argc == 1)
		output = new Test::TextOutput(Test::TextOutput::Verbose);
	else
	{
		const char* arg = argv[1];
		if (strcmp(arg, "--compiler") == 0)
			output = new Test::CompilerOutput;
		else if (strcmp(arg, "--html") == 0)
			output =  new Test::HtmlOutput;
		else if (strcmp(arg, "--text-terse") == 0)
			output = new Test::TextOutput(Test::TextOutput::Terse);
		else if (strcmp(arg, "--text-verbose") == 0)
			output = new Test::TextOutput(Test::TextOutput::Verbose);
		else
		{
			std::cout << "invalid commandline argument: " << arg << std::endl;
			usage(); // will not return
		}
	}
	
	return output;
}

// Main test program
//
int main (int argc, char* argv[])
{
    initialiseJuce_GUI();

    int return_value = EXIT_SUCCESS;

	try
	{
		// Demonstrates the ability to use multiple test suites
		//
		Test::Suite ts;
		ts.add (new ScriptingTestSuite);
		ts.add (new CompareTestSuite);
		ts.add (new ThrowTestSuite);

		// Run the tests
		//
		SharedPointer<Test::Output> output (cmdline(argc, argv));
		ts.run(*output, true);

		Test::HtmlOutput* const html = dynamic_cast<Test::HtmlOutput*>(output.get());
		if (html)
			html->generate (std::cout, true, "MyTest");
	}
	catch (...)
	{
		std::cout << "unexpected exception encountered" << std::endl;
		return_value = EXIT_FAILURE;
	}

    shutdownJuce_GUI();

	return return_value;
}

