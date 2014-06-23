/* Function to select a text in textarea with a click */
function select(text)
{
     var t = document.getElementById(text).innerHTML;
     alert(t);
}

/* Function to submit a form with a Enter button */
function send(t, e) 
{
    if ((e.which && e.which == 13) || (ev.keyCode && e.keyCode == 13))
	{
        document.getElementById(t).click();
		return false;
    }
	else
	{
		return true;
	}
}