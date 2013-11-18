function sendComand(comando){
	 $.ajax({
        url: "http://localhost:8000/ajax/ir/",
        type:"post",
        dataType: "json",
        error: function(XMLHttpRequest, textStatus, errorThrown) {
            alert(errorThrown);
        },
        success: function(data, textStatus, XMLHttpRequest) {
            alert(data)
        }
    });

}