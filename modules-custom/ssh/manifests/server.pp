/**
 * 
 * Installs and configures the SSH server
 * 
 */
class ssh::server {
    
  include ssh::server::install, ssh::server::config, ssh::server::service
  
}
