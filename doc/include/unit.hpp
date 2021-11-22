#ifndef UNIT_HPP
#define UNIT_HPP

#include<cmath>

namespace cyg{
	typedef long double real;

	class unit{
	public:
		real number_to_std;
        long long exp;

		constexpr explicit unit(real&& nts,long long&& _exp):number_to_std(nts),exp(_exp){}

		real to_std(const real& value)const{
			return value*number_to_std*std::pow(10,exp);
		}

		real to_std(real&& value)const{
			return value*number_to_std*std::pow(10,exp);
		}
	};

	/*distance*/
	constexpr unit m(1,3),km(1,6),dm(1,2),cm(1,1),mm(1,0),um(1,-3),nm(1,-6);

	/*time*/
	constexpr unit sec(1,3),min(6,4),h(3.6,6),ms(1,0),us(1,-3),ns(1,-6);

    /*byte*/
    constexpr unit Mb(real(1/8.0),0),MB(1,0),Kb(real(1/(1024*8.0)),0),KB(real(1/1024.0),0);

	template<const unit& u1,const unit& u2>
	real convert(const real& value){
		return u1.to_std(value)/(u2.number_to_std*std::pow(10,u2.exp));
	}
}

#endif
