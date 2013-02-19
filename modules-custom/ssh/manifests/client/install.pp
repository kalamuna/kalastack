/**
 * 
 * Installs the SSH client
 * 
 */
class ssh::client::install {
    
    package { "openssh-client":
        ensure => "present",
    }
}

