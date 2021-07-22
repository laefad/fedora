#pragma once

#include <vector>

#include "Function.h"
#include "BasicType.h"

namespace fedora {

	class FunCall {
	private:
		std::shared_ptr<fedora::function::Function> funct;
		std::vector<fedora::types::BasicType> args;
	public:
		FunCall (
			std::shared_ptr<fedora::function::Function> funct,
			std::vector<fedora::types::BasicType> args
			) 
			: funct(funct), args(args)
		{}

		std::unique_ptr<fedora::types::BasicType> execute() {
			
		}
	};

}
