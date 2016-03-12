#ifndef		ISELECT_HPP_
# define	ISELECT_HPP_

# include	"FDSet.hpp"

class		ISelect
{
 public:

  virtual ~ISelect() {}

  virtual bool	call(const FDSet* read, const FDSet* write) = 0;
};

#endif		// !ISELECT_HPP_
