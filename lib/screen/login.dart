import 'package:flutter/material.dart';
import 'package:flutter/widgets.dart';
import 'package:todo_list_app/colors/colors.dart';

class LoginScreen extends StatefulWidget{
  const LoginScreen({super.key});

  @override
  State<LoginScreen> createState()=> Login_ScreenState();

}
 
class Login_ScreenState extends State<LoginScreen>{
  @override
  Widget build(BuildContext){
    return Scaffold(
      backgroundColor: backgroundColors,
      body: SafeArea(child: SingleChildScrollView(
        child:  Column(
          children: [
            const SizedBox(height:20),
            image(),
            const SizedBox(height:50),
            Container(
              decoration: BoxDecoration(
                color: Colors.white,
                borderRadius: BorderRadius.circular(15),

              ),
              child: const TextField(),
            )
            
            // const Padding(
            //   padding:EdgeInsets.symmetric(horizontal: 15),
            // ),
            // Container(
            //   width:double.infinity,
            //   height:300,
            //   decoration:const BoxDecoration(
            //     image: DecorationImage(image: AssetImage('images/login.jpeg'),
              //   fit: BoxFit.cover,
              //   ),
              // ) ,
              // )
            ],
          ),
        ),
      ),
    );
  }

  Padding image(){
      return Padding(
              padding:const EdgeInsets.symmetric(horizontal: 15),
            child:Container(
              width:double.infinity,
              height:300,
              decoration:const BoxDecoration(
                image: DecorationImage(
                  image: AssetImage('images/login.jpeg'),
                fit: BoxFit.cover,
                ),
              ) ,
            ),
        );
      }
}