#ifndef FORMAT_HPP
#define FORMAT_HPP

#include<string>
#include<typeinfo>
#include<algorithm>

namespace cyg{

    std::string format(std::string fmt){
        return fmt;
    }

    template<typename hT,typename...argsT>
    std::string format(std::string fmt,const std::pair<std::string,hT>& hArg,const std::pair<std::string,argsT>&...Args){
        if(fmt.find("{"+hArg.first+"}")<fmt.size()){
            fmt.replace(fmt.find("{"+hArg.first+"}"),("{"+hArg.first+"}").size(),hArg.second);
            return format(fmt,Args...);
        }
        else
            return fmt;
    }
}

#endif //FORMAT_HPP
