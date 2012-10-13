/**
 * 
 * Installs and configures the SSH server
 * 
 */
class ssh::server {
    
  include ssh::server::install
  include ssh::server::service
  
}
