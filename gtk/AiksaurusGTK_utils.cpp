/*
 * AiksaurusGTK - A GTK interface to the AikSaurus library
 * Copyright (C) 2001 by Jared Davis
 *
 * This program is free software; you can redistribute it and/or
 * modify it under the terms of the GNU General Public License
 * as published by the Free Software Foundation; either version 2
 * of the License, or (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program; if not, write to the Free Software
 * Foundation, Inc., 59 Temple Place - Suite 330, Boston, MA
 * 02111-1307, USA.
 */

// header file that we are implementing here.
#include "AiksaurusGTK_utils.h"

// cstring needed for strlen.
#include <cstring>

// new needed for nothrow.
#include <new>


bool AiksaurusGTK_strEquals(const char* lhs, const char* rhs)
{
	if ((!lhs) || (!rhs))
		return (lhs == rhs);
	
	register int i = 0;
	while(lhs[i] != '\0')
	{
		if (rhs[i] != lhs[i])
			return false;
		
		++i;
	}

	return (rhs[i] == '\0');
}


char* AiksaurusGTK_strCopy(const char* str)
{	
	char* ret;
	
	if (!str)
	{
		ret = new(nothrow) char[1];
		
		if (!ret)
			return ret;
		
		ret[0] = '\0';
		
	}

	else
	{
		const int len = strlen(str);

		ret = new(nothrow) char[len+1];
	
		if (!ret)
			return ret;
		
		for(register int i = 0;i < len;++i)
		{
			ret[i] = str[i];
		}

		ret[len] = '\0';
	}

	return ret;
}


char* AiksaurusGTK_intToString(int x)
{
	if (x == 0)
	{
		char* ret = new(nothrow) char[2];
		
		if (!ret) 
			return 0;
		
		ret[0] = '0';
		ret[1] = '\0';
		return ret;
	}
	
	
	bool minus = false;
	
	// first, figure out number of digits needed.
	unsigned int numdigits = 0;
	if (x < 0) 
	{
		minus = true;   // mark that we are negative.
		numdigits++;	// create space for a minus sign.
		x = -x;         // change into postive number.
	}

	if (x == 0)
		numdigits = 1;
	else
	{
	
 		int digitshelper = x;
		while(digitshelper > 0)
		{
			digitshelper /= 10;
			numdigits++;
		}
	}

	// We will build a string from the back forward.
	char* ret = new(nothrow) char[numdigits+1];

	if (ret)
	{
		ret[numdigits] = '\0';
		
		while(x > 0)
		{
			numdigits--;
			ret[numdigits] = '0' + (x % 10);
			x /= 10;
		}
		
		if (minus)
			ret[0] = '-';
	}

	return ret;
}


char* AiksaurusGTK_strConcat(const char* a, const char* b)
{
	int len_a = strlen(a);
	int len_b = strlen(b);

	char* ret = new(nothrow) char[len_a + len_b + 1];

	if (!ret)
		return ret;

	register int i = 0;
	
	while(i < len_a)
	{
		ret[i] = a[i];
		++i;
	}
	
	while(i < len_b + len_a)
	{
		ret[i] = b[i - len_a];
		++i;
	}
	
	ret[len_a + len_b] = '\0';

	return ret;
}
