/**
* Copyright 2015 IBM Corp. All Rights Reserved.
*
* Licensed under the Apache License, Version 2.0 (the "License");
* you may not use this file except in compliance with the License.
* You may obtain a copy of the License at
*
*      http://www.apache.org/licenses/LICENSE-2.0
*
* Unless required by applicable law or agreed to in writing, software
* distributed under the License is distributed on an "AS IS" BASIS,
* WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
* See the License for the specific language governing permissions and
* limitations under the License.
*
*/

#include "Alchemy.h"

REG_SERIALIZABLE( Alchemy );
RTTI_IMPL( Alchemy, IService );


Alchemy::Alchemy() : IService("AlchemyV1")
{}

//! ISerializable
void Alchemy::Serialize(Json::Value & json)
{
	IService::Serialize(json);
}

void Alchemy::Deserialize(const Json::Value & json)
{
	IService::Deserialize(json);
}

//! IService interface
bool Alchemy::Start()
{
	if (!IService::Start())
		return false;

	if (!StringUtil::EndsWith(m_pConfig->m_URL, "calls"))
	{
		Log::Error("Alchemy", "Configured URL not ended with calls");
		return false;
	}
	if (m_pConfig->m_User.size() == 0)
	{
		Log::Error("Alchemy", "API-Key expected in user field.");
		return false;
	}

	return true;
}

void Alchemy::GetServiceStatus(ServiceStatusCallback a_Callback)
{
	a_Callback(ServiceStatus(m_ServiceId, true));
}

void Alchemy::GetChunkTags(const std::string & a_Text,
	Delegate<const Json::Value &> a_Callback )
{
	std::string parameters = "/text/TextGetChunkTags";
	parameters += "?apikey=" + m_pConfig->m_User;
	parameters += "&outputMode=json";
	parameters += "&text=" + StringUtil::UrlEscape( a_Text );

	new RequestJson(this, parameters, "GET", NULL_HEADERS, EMPTY_STRING, a_Callback);
}

void Alchemy::GetPosTags(const std::string & a_Text,
	Delegate<const Json::Value &> a_Callback )
{
	std::string parameters = "/text/TextGetPOSTags";
	parameters += "?apikey=" + m_pConfig->m_User;
	parameters += "&outputMode=json";
	parameters += "&text=" + StringUtil::UrlEscape( a_Text );

	new RequestJson(this, parameters, "GET", NULL_HEADERS, EMPTY_STRING, a_Callback);
}
