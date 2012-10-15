/**
 * 
 * Generates SSH keys for the kala_user
 * 
 */
class ssh::server::config {
        
    # autogen ssh keys
    exec { "sshkeygen":
      path => "/bin:/usr/bin",
      unless => "cat /home/${::kala_user}/.ssh/id_rsa.pub",
      command => "sudo -u ${::kala_user}  ssh-keygen",
      require => Class["ssh:server::install"],
      notify => Class["ssh::server::service"],
    }
    
}