KALABOX 
=====================
A local php development environment. 


Supported 
=====================
Drupal 6, 7


Changelog
======================
Version 1.0
- proof of concept


Installation
======================

SET UP YOUR SERVER
1. Install Ubuntu 12.04 LTS Server* (git config --global user.name "Your Name"can use Desktop Version if you are not going to virtualize)
2. run sudo apt-get update/upgrade
3. run sudo apt-get install puppet
4. run sudo puppet agent --verbose --test --server kalabox.kalamuna.com

*If running in Virtual Box make sure you use Bridged Networking

COMMON POST INSTALLATION SERVER SET UP
1. run ssh-keygen
2. run git config --global user.name "Your Name"
3. run git config --global user.email name@domain.example
4. If running natively add "xdebug.kala" to 127.0.0.1 in /etc/hosts

COMMON POST INSTALLTION HOST SET UP
1. If running in a Virtual Box add "HOST IP ADDRESS   xdebug.kala" to your server's /etc/hosts
2. In your host's /etc/hosts add "SERVER IP ADDRESS   kala, php.kala, SERVERHOSTNAME
