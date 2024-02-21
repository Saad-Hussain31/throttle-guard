/**
  author: Saad Hussain <saadnasir31@gmail.com>
  date: 13-02-2024

  RateLimiter class that contain functions for handling incoming requests,
  checking against rate limits, and returning appropriate responses.
*/

#pragma once
#include "drogon/HttpRequest.h"
#include "drogon/HttpResponse.h"
#include "redis_client.h"
#include "rule.h"

class RateLimiter {
public:
  RateLimiter(RedisClient &redis_client);
  ~RateLimiter();

  drogon::HttpRequestPtr handle_request(const drogon::HttpRequestPtr &request);

private:
  RedisClient m_redis_client;
  std::unordered_map<std::string, Rule> m_rules;

  bool is_allowed(const std::string &domain,
                  const std::vector<std::string> &descriptors);
  void parse_config_file(const std::string &config_file);
  void lograte_limited_request(const drogon::HttpRequest &request);
};