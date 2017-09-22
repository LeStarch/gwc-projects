/**
 * This file contains the entry point for the gwc app project code. The initialization of
 * the Cordova App is a bit complex, and has been configured to point to the main function
 * in this file.  This lowers the leraning curev for our students.
 *
 * @author lestarch (Michael Starch)
 */
/**
 * Main function entry point for GWC project code. This function runs after the app has 
 * been initialized and all resources are prepared for execution.  It is passed the 
 * "app" object from cordova in case that is needed.
 * @param app - Cordova app object
 */
function main(app)
{
    //Start your GWC code here
    var button = document.getElementById("change-button");
    //Set a function to call on a click of the button
    button.onclick = change;
}
/**
 * Changes the text of the paragraph with id "paragraph-1"
 */
function change()
{
    //Read the value
    var input = document.getElementById("textbox-1").value;
    //Put it into an alert pop-up 
    alert("Input was: "+input);
    var is_checked = document.getElementById("checkbox-1").checked;
    if (is_checked)
    {
        alert("You checked the box");
    } 
    else
    {
        alert("You unchecked the box");
    }
    document.getElementById("paragraph-1").innerHTML = "This is new text";
}
