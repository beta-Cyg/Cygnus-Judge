#ifndef UNIT_HPP
#define UNIT_HPP

namespace cyg{
	typedef long double real;

	class unit{
	public:
		real number_to_std;

		constexpr unit(real&& nts):number_to_std(nts){}

		const real to_std(const real& value)const{
			return value*number_to_std;
		}

		const real to_std(real&& value){
			return value*number_to_std;
		}
	};

	/*distance*/
	constexpr unit m(1e3),km(1e6),dm(1e2),cm(1e1),mm(1e0),um(1e-3),nm(1e-6);

	/*time*/
	constexpr unit sec(1e3),min(60*1e3),h(3600*1e3),ms(1e0),us(1e-3),ns(1e-6);

	template<const unit& u1,const unit& u2>
	const real convert(const real& value){
		return u1.to_std(value)/u2.number_to_std;
	}
}

#endif
