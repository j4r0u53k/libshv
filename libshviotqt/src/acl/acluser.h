#pragma once

#include "../shviotqtglobal.h"
#include "aclpassword.h"

#include <vector>

namespace shv { namespace chainpack { class RpcValue; } }

namespace shv {
namespace iotqt {
namespace acl {

struct SHVIOTQT_DECL_EXPORT AclUser
{
	//std::string name;
	AclPassword password;
	std::vector<std::string> roles;

	AclUser() {}
	AclUser(AclPassword p, std::vector<std::string> roles)
		: password(std::move(p))
		, roles(std::move(roles))
	{}
	//const std::string userName() const {return login.user;}
	bool isValid() const {return password.isValid();}
	shv::chainpack::RpcValue toRpcValue() const;
	static AclUser fromRpcValue(const shv::chainpack::RpcValue &v);
};

} // namespace acl
} // namespace iotqt
} // namespace shv

