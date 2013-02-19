/**
 * 
 * Installs and configures both the SSH server and client
 * 
 */
class ssh {
    
    include ssh::server
    include ssh::client
    
}
