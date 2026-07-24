/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bigint.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: toruinoue <toruinoue@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/07/18 13:50:49 by toruinoue         #+#    #+#             */
/*   Updated: 2026/07/18 14:46:49 by toruinoue        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef BIGINT
#define BIGINT

#include <sstream>
#include <iostream>
#include <string>
#include <cstdlib>

class bigint
{
	private:
		std::string str;
	
	public:
		bigint();
		bigint(unsigned int num);
		bigint(const bigint& source);

		// std::string getStr() const;
		std::string getStr() const;

		
		bigint& operator=(const bigint& source);
		
		bigint	operator+(const bigint& other) const;
		bigint&	operator+=(const bigint& other);

		bigint& operator++();
		bigint operator++(int);

		// shift with num
		bigint	operator<<(unsigned int n) const;
		bigint	operator>>(unsigned int n) const;
		bigint& operator<<=(unsigned int n);
		bigint& operator>>=(unsigned int m);

		// shift with object
		bigint	operator<<(const bigint& other) const;
		bigint	operator>>(const bigint& other) const;
		bigint&	operator<<=(const bigint& other);
		bigint& operator>>=(const bigint& other);
		
		// 5
		bool	operator==(const bigint& other) const;
		bool	operator!=(const bigint& other)	const;
		bool	operator<(const bigint& other) const;
		bool	operator>(const bigint& other)	const;
		bool	operator<=(const bigint& other) const;
		bool	operator>=(const bigint& other)	const;

};

std::ostream& operator<<(std::ostream& output, const bigint& obj);

#endif
