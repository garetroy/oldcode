$( document ).ready(function(){
	$("#temphide").hide()
	$("#container").hide();
	$("#submit-btn").click(function(){
		var shower_min = 2.1*parseInt($("#a").val()),
			toilet_flush = 1.6*parseInt($("#b").val()),
			times_laundry = (28*parseInt($("#c").val())/7),
			times_dishes = (5*parseInt($("#e").val())/7),
			water_drinking = (8*parseInt($("#d").val())/128);
		var total_water = shower_min + toilet_flush + times_laundry + water_drinking + times_dishes // function here
		var decimal_water = total_water/1.32
		var somali_water = Math.round(decimal_water)
		$("#container").show();
		$("#temphide").show();
		$("#text").remove();
		$("#textarea").append("<div id='text'>You use the same amount of water in one day, on average, as <b><div id='bignumber'>" + somali_water + "</div></b> people in Somalia</div>");
	});

	$("#redobtn").click(function(){
		$("#main").show();
		$("#text").remove();
	});
});