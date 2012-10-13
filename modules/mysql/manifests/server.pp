/**
 * 
 * Loads subclasses to complete the server install and config
 * 
 */
class mysql::server {
    
  include mysql::server::install, mysql::server::config, mysql::server::service
  
}