/**
 * 
 * Prepend a line to a file if that line doesn't already exist
 * 
 */
define prepend_if_no_such_line ( 
    $file, 
    $line, 
    $refreshonly = 'FALSE',
) {
    
    exec { "/usr/bin/perl -p0i -e 's/^/$line\n/;' '$file'":
        unless      => "/bin/grep -Fxqe '$line' '$file'",
        path        => "/bin",
        refreshonly => $refreshonly,
    }
    
}