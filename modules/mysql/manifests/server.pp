
class mysql::server {
  include mysql::server::install, mysql::server::config, mysql::server::service
}