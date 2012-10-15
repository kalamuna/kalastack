/**
 * 
 * Set git global git user and email
 * 
 */
class git::config {
   
    # Sets the git username
    exec { "gitconfigusername":
      path => "/bin:/usr/bin",
      unless => "grep name /home/${::kala_user}/.gitconfig",
      command => "sudo -u ${::kala_user} git config --global user.name \"${::kala_name}\"",
      require => Class[git::install],
    }
    
    # Sets the git email
    exec { "gitconfiguseremail":
      path => "/bin:/usr/bin",
      unless => "grep email /home/${::kala_user}/.gitconfig",
      command => "sudo -u ${::kala_user} git config --global user.email \"${::kala_user}@${::hostname}\"",
      require => Class[git::install],
    }
    
}
