/**
 * 
 * Installs the SSH client
 * 
 */
class ssh::client::install {
    
    package { "openssh-client":
        ensure => "1:5.9p1-5ubuntu1",
    }
}

