/*
 * Test.cpp
 *
 *  Created on: 21 apr. 2017
 *      Author: Acer
 */

#include <Test.h>
#include <Memoryleak.h>
#include <string.h>
#include <Windows.h>
#include <TestFailsException.h>
#include <ConsoleASCIIcode.h>

std::mutex Test::sLogMutex;

Test::Test(std::string name)
	: m_failed(false)
	, m_name(name)
	, m_resultMessage("")
{
}

Test::~Test() {
}

void Test::run(){
	FILETIME ftStart, ftEnd;
	double dElapsed;
	std::string logMsg(ConsoleASCIIcode::getForegroundSequence(ConsoleASCIIcode::WHITE));
	logMsg += "Name: " + m_name;
	logMsg += "\nStatus: ";

	try{
		::GetSystemTimeAsFileTime(&ftStart);
		m_failed = !test();
		::GetSystemTimeAsFileTime(&ftEnd);
	}
	catch (TestFailsException &e){
		::GetSystemTimeAsFileTime(&ftEnd);
		appendToResultMessage("Failure message: ");
		appendToResultMessage(e.getMessage());
	}
	catch (std::exception &e) {
		::GetSystemTimeAsFileTime(&ftEnd);

		appendToResultMessage("Error has occurd: ");
		appendToResultMessage(e.what());
		appendToResultMessage("\n");

		m_failed = true;
	}

	if (m_failed){
		logMsg += ConsoleASCIIcode::getForegroundSequence(ConsoleASCIIcode::RED);
		logMsg += "failed";
	} else {
		logMsg += ConsoleASCIIcode::getForegroundSequence(ConsoleASCIIcode::GREEN);
		logMsg += "succeed";
	}
	logMsg += ConsoleASCIIcode::getForegroundSequence(ConsoleASCIIcode::WHITE) + " (";

	dElapsed = (ftEnd.dwLowDateTime - ftStart.dwLowDateTime) / 10000.0;
	if (dElapsed < 1500){
		logMsg += std::to_string(dElapsed) + " ms)\n\n";
	} else {
		logMsg += std::to_string(dElapsed/1000) + " s)\n\n";
	}

	m_resultMessage = logMsg + m_resultMessage;
	printResults();
}



void Test::fail(std::string message){
	m_failed = true;
	throw TestFailsException(message);
}

void Test::printResults() {
	m_resultMessage =
			"\n------------------------------------------------------------\n" +
			m_resultMessage +
			"\n------------------------------------------------------------\n";
	log(m_resultMessage);
}

void Test::appendToResultMessage(std::string message) {
	m_resultMessage += message;
}

const std::string& Test::getName() const {
	return m_name;
}
