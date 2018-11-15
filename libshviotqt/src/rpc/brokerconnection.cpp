#include "brokerconnection.h"
#include "../utils/fileshvjournal.h"

#include <shv/core/log.h>

#include <fstream>

namespace cp = shv::chainpack;

namespace shv {
namespace iotqt {
namespace rpc {
/*
BrokerConnectionAppCliOptions::BrokerConnectionAppCliOptions()
{
	removeOption("shvJournal.dir");
	removeOption("shvJournal.fileSizeLimit");
	removeOption("shvJournal.dirSizeLimit");

	addOption("exports.shvPath").setType(cp::RpcValue::Type::String).setNames("--export-path").setComment("Exported SHV path");
}
*/
BrokerConnection::BrokerConnection(QObject *parent)
	: Super(parent)
{
}

void BrokerConnection::setOptions(const chainpack::RpcValue &slave_broker_options)
{
	if(slave_broker_options.isMap()) {
		const cp::RpcValue::Map &m = slave_broker_options.toMap();

		DeviceAppCliOptions device_opts;

		const cp::RpcValue::Map &login = m.value(cp::Rpc::KEY_LOGIN).toMap();
		device_opts.setUser(login.value("user").toString());
		device_opts.setPassword(login.value("password").toString());
		device_opts.setLoginType(login.value("type").toString());

		const cp::RpcValue::Map &rpc = m.value("rpc").toMap();
		if(rpc.count("heartbeatInterval") == 1)
			device_opts.setHeartbeatInterval(rpc.value("heartbeatInterval").toInt());
		if(rpc.count("reconnectInterval") == 1)
			device_opts.setReconnectInterval(rpc.value("reconnectInterval").toInt());
		if(rpc.count("metaTypeExplicit") == 1)
			device_opts.setMetaTypeExplicit(rpc.value("metaTypeExplicit").toBool());

		const cp::RpcValue::Map &device = m.value(cp::Rpc::KEY_DEVICE).toMap();
		if(device.count("id") == 1)
			device_opts.setDeviceId(device.value("id").toString());
		if(device.count("idFile") == 1)
			device_opts.setDeviceIdFile(device.value("idFile").toString());
		if(device.count("mountPoint") == 1)
			device_opts.setMountPoint(device.value("mountPoint").toString());

		Super::setCliOptions(&device_opts);
	}
}

} // namespace rpc
} // namespace iotqt
} // namespace shv