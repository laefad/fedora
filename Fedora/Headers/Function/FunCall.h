#pragma once
#include "Function.h"
#include <vector>
#include "Headers/Types/BasicType.h"

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

		fedora::types::BasicType execute() {
			
		}
	};

}
