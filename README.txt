This Drupal 7 module reads in the file form.xml and creates a web form using
Form API. The module has only been written for demonstration purposes and
hasn't been tested with any other xml file. Moreover, the web form it creates
does not save form data to the Drupal database or pass on the data to an
external site - it simply redirects the user on successful form submission.

Usage
=====
After you have installed this module (see below) on a Drupal 7 website $ROOT
you can configure it here: $ROOT/admin/config/content/xmltoform

On this configuration page you can set:

1, the Path to the web form on your local site (default is xmltoform); and the
2, URL for the website the form redirects to (default http://www.logicnow.com)

Installation instructions
=========================

After setting up a working Drupal installation, go to sites/all/modules or
sites/default/modules (you may need to create this folder) or a subdirectory
such as sites/all/modules/contrib or sites/all/modules/custom

You can download the latest version of xmltoform to your chosen modules folder
from https://github.com/drmiw/xmltoform/archive/master.zip or you can use git
to clone the module to a xmltoform subfolder and/or pull the most recent
changes from within the xmltoform subfolder.

On the command line that would be:

$ git clone https://github.com/drmiw/xmltoform.git
$ cd xmltoform
$ git pull

With the xmltoform module code in place you can use drush (if installed) to
enable the module and download its dependencies as follows:

$ drush en xmltoform

Alternatively you can log in to your website and enable the xmltoform module
at $ROOT/admin/modules where $ROOT is your website's address. You will be
prompted to install the module's dependencies too and the Drupal 7 versions of
these modules can be downloaded from:

* https://www.drupal.org/project/date
* https://www.drupal.org/project/clientside_validation

Date picker functionality is provided by the required Date module and two sub
modules - one of which is Date API which will warn you that it "requires that
you set up the site timezone and first day of week settings and the date format
settings to function correctly.

This is important because the date format for the 'Date of birth' fieldset
depends on the 'Short' Date Type format, which is set in the standard way at
$ROOT/admin/config/regional/date-time.

Client side validation for the web form is provided by the required 'Clientside
Validation' module.

Testing
=======
To run functional tests of the code you must first enable the Testing module
(a Core Drupal module) and then go to $ROOT/admin/config/development/testing/.