#pragma once

#include <stddef.h>

class ASymbol
{
	private:
		size_t	_size;
		size_t	_line;
		size_t	_column;
	protected:
		ASymbol(void);
	public:
		virtual ~ASymbol(void);

		void	setSize(size_t n);
		void	setLine(size_t n);
		void	setColumn(size_t n);
		size_t	getSize(void) const;
		size_t	getLine(void) const;
		size_t	getColumn(void) const;
		
		virtual ASymbol*	clone(void) const = 0;
};
