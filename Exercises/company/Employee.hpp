/*
 * Copyright (C) 2015    Raphaël Beamonte <raphael.beamonte@polymtl.ca>
 * All rights reserved.
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions
 * are met:
 * 1. Redistributions of source code must retain the above copyright
 *    notice, this list of conditions and the following disclaimer.
 * 2. Redistributions in binary form must reproduce the above copyright
 *    notice, this list of conditions and the following disclaimer in the
 *    documentation  and/or other materials provided with the distribution.
 * 3. Neither the names of the copyright holders nor the names of any
 *    contributors may be used to endorse or promote products derived from this
 *    software without specific prior written permission.
 *
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS"
 * AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
 * IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE
 * ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE
 * LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR
 * CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF
 * SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS
 * INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN
 * CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE)
 * ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE
 * POSSIBILITY OF SUCH DAMAGE.
 *
 * This file has been created for the purpose of the INF1010
 * course of École Polytechnique de Montréal.
 * Version: 14/1.0
 */

#pragma once

#include <string>
using namespace std;

namespace company {

/**
 * @brief The Employee class to describe an employee
 */
class Employee
{
public:
	// Constructors
	/**
	 * @brief Employee The constructor receiving the employee name and its salary
	 * @param name The employee name (default: unknown)
	 * @param salary The employee salary (default: 0)
	 */
	Employee(string name = "unknown", double salary = 0);
    /**
     * @brief ~Employee The destructor
     */
    virtual ~Employee();

	// Getters
	/**
	 * @brief getSalary To get the employee salary
	 * @return The employee salary
	 */
	virtual double getSalary() const;
	/**
	 * @brief getName To get the employee name
	 * @return The employee name
	 */
	virtual string getName() const;

	// Setters
	/**
	 * @brief setSalary To change the employee salary
	 * @param salary The new salary of the employee
	 */
	void setSalary(double salary);

private:
	// Attributes
	/**
	 * @brief name_ To store the employee name
	 */
	string name_;
	/**
	 * @brief salary_ To store the employee salary
	 */
	double salary_;
};

}

