md_commodiyt_save()
/*
  ΢�̲������� ��������
*/
{
    char base_str1[500],base_str2[500],itemid_or_barcode[20],supply_unit_num_id[20];

	//��ȡ�̶�������ID supply_unit_num_id
	strcpy(supply_unit_num_id,lr_eval_string(mendian_supply_unit_num_id()));
	lr_save_string(supply_unit_num_id,"supply_unit_num_id");;
    //��ȡ�̶������̵Ĺ̶���ƷID
	strcpy(itemid_or_barcode,lr_eval_string(mendian_itemid_barcode()));
	lr_save_string(itemid_or_barcode,"itemid_or_barcode");

    //����1
    strcpy(base_str1,lr_eval_string("{\"type_num_id\":1,\"remark\":\"\","
									"\"supply_unit_num_id\":{supply_unit_num_id},"
									"\"sub_unit_num_id\":{md_sub_unit_num_id},"
									"\"apply_logistics_type\":0,"
									"\"apply_num_id\":\"{md_sequence_num}\","
									"\"div_num_id\":0,\"order_date\":\"{order_date}\"}"));
	lr_save_string(base_str1,"base_str1");
	strcpy(base_str1,base64_encode(lr_eval_string("{base_str1}"),strlen(base_str1)));
	lr_save_string(base_str1,"base_str1");// ����base64
	web_reg_find("Text=\"code\":0","Savecount=apply_hdr_save_code_count",LAST);//���ü���
    web_add_header("Authorization","{md_author}");
	web_set_sockets_option("SSL_VERSION","TLS");
    lr_start_transaction("apply_hdr_save");
    web_custom_request("apply_hdr_save",
		"URL={url}",
		"Method=POST",
		"Resource=0",
		"RecContentType=application/x-www-form-urlencoded",
		"Referer=",
		"Mode=HTTP",
		"EncType=application/x-www-form-urlencoded",
		"Body=timestamp={timestamp}&method=ykcloud.scm.replenish.apply.hdr.save&sid={md_sid}&sign=&params={base_str1}",
		LAST);
	if(atoi(lr_eval_string("{apply_hdr_save_code_count}"))>0){
			lr_end_transaction("apply_hdr_save",LR_PASS);
		}else{
            lr_end_transaction("apply_hdr_save",LR_FAIL);
			 if (rerun_value()==0) {
				  return -1;
			 }
		}

    //����2
    strcpy(base_str2,lr_eval_string("{\"qty\":1{dayhour}.0,\"sub_unit_num_id\":{md_sub_unit_num_id},"
									"\"package_qty\":1{dayhour}.0,\"pmt_qty\":0.0,\"series\":\"\","
									"\"apply_num_id\":\"{md_sequence_num}\",\"item_num_id\":{itemid_or_barcode},"
									"\"order_date\":\"{order_date}\"}"));
	lr_save_string(base_str2,"base_str2");
	strcpy(base_str2,base64_encode(lr_eval_string("{base_str2}"),strlen(base_str2)));
	lr_save_string(base_str2,"base_str2");// ����base64
	web_reg_find("Text=\"code\":0","Savecount=apply_dtl_save_code_count",LAST);//���ü���
	web_reg_save_param("md_series","RB=\"}","LB=\"series\":\"",LAST);//�ù�������ȡֵ 
    web_add_header("Authorization","{md_author}");
	web_set_sockets_option("SSL_VERSION","TLS");
    lr_start_transaction("apply_dtl_save");
    web_custom_request("apply_dtl_save",
		"URL={url}",
		"Method=POST",
		"Resource=0",
		"RecContentType=application/x-www-form-urlencoded",
		"Referer=",
		"Mode=HTTP",
		"EncType=application/x-www-form-urlencoded",
		"Body=timestamp={timestamp}&method=ykcloud.scm.replenish.apply.dtl.save&sid={md_sid}&sign=&params={base_str2}",
		LAST);
	if(atoi(lr_eval_string("{apply_dtl_save_code_count}"))>0){
			lr_end_transaction("apply_dtl_save",LR_PASS);
		}else{
            lr_end_transaction("apply_dtl_save",LR_FAIL);
			 if (rerun_value()==0) {
				  return -1;
			 }
		}
	return 0;
}
