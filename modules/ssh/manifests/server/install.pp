/**
 * 
 * Installs the SSH server
 * 
 */
class ssh::server::install {
    
    package { "openssh-server":
        ensure => "1:5.9p1-5ubuntu1",
    }
    
}
