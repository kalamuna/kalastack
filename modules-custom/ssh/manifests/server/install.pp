/**
 * 
 * Installs the SSH server
 * 
 */
class ssh::server::install {
    
    package { "openssh-server":
        ensure => "present",
    }
    
}
