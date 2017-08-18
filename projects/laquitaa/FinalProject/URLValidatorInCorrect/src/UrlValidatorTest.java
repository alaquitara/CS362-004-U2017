/*/*
 * Licensed to the Apache Software Foundation (ASF) under one or more
 * contributor license agreements.  See the NOTICE file distributed with
 * this work for additional information regarding copyright ownership.
 * The ASF licenses this file to You under the Apache License, Version 2.0
 * (the "License"); you may not use this file except in compliance with
 * the License.  You may obtain a copy of the License at
 *
 *      http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */


import junit.framework.TestCase;





/**
 * Performs Validation Test for url validations.
 *
 * @version $Revision: 1128446 $ $Date: 2011-05-27 13:29:27 -0700 (Fri, 27 May 2011) $
 */
public class UrlValidatorTest extends TestCase {

   private boolean printStatus = false;
   private boolean printIndex = false;//print index that indicates current scheme,host,port,path, query test were using.

   public UrlValidatorTest(String testName) {
      super(testName);
   }

   
   private void tyAssert(int current, int test){					//A basic assert that tells us when a test passed and failed
       if(current < test){										//We wrote something like this when testing Dominion
           System.out.printf("Test %d failed \n", test);
       }
       else {
    	   System.out.printf("Test %d is fine\n", test);
       }
   }

   
   
   public void manualTesting()
   {
	   UrlValidator urlVal = new UrlValidator(null, null, UrlValidator.ALLOW_ALL_SCHEMES);		//These are manual combinations I did. There are some errors in the tests
	   System.out.println(urlVal.isValid("http://www.amazon.com"));								
	   
	   int currentCount = 0;
       int testingCount = 0;
       
       if(urlVal.isValid("http://amazon.com")){			//Basic structure for all the tests
           currentCount++;								//If isValid() does what we expect, we increment the currentCount of correct tests
       }
       testingCount++;									//After each test, we then increment the test count and compare it to the currentCount
       tyAssert(currentCount,testingCount);				//This assert statement will tell us if the test is broken or its fine	

       if(urlVal.isValid("http://www.amazon.com")){			//Should pass
           currentCount++;
       }
       testingCount++;
       tyAssert(currentCount,testingCount);
       
       if(urlVal.isValid("https://www.amazon.com")){	//Should be fine
           currentCount++;
       }
       testingCount++;
       tyAssert(currentCount,testingCount);
       
       if(urlVal.isValid("http://www.amazon.com:23")){	//Known port
           currentCount++;
       }
       testingCount++;
       tyAssert(currentCount,testingCount);
       
       if(urlVal.isValid("gtp://www.amazon.com")){		//Should not be valid URL
           currentCount++;
       }
       testingCount++;       
       tyAssert(currentCount,testingCount);       

       
       if(!urlVal.isValid("http://www.amazon")){	//Invalid URL while stating it's not valid. Should pass	
           currentCount++;
       }
       testingCount++;
       tyAssert(currentCount,testingCount);
       
       if(!urlVal.isValid("http:/www.amazon.com")){		//One slash
           currentCount++;
       }
       testingCount++;
       tyAssert(currentCount,testingCount);   

       
       if(!urlVal.isValid("http://www.amazon.com:123c")){
           currentCount++;
       }
       testingCount++;
       tyAssert(currentCount,testingCount);
       
       if(urlVal.isValid("http://ww.amazon.com")){		//Invalid URL
           currentCount++;
       }
       testingCount++;
       tyAssert(currentCount,testingCount);
       
       if(!urlVal.isValid("http://www.amazon___.com")){	 //Bunch of underscores
           currentCount++;
       }       
       testingCount++;
       tyAssert(currentCount,testingCount);

       
       if(!urlVal.isValid("http://257.258.259.260:80")){  //Ports should be out of range
           currentCount++;
       }
       testingCount++;
       tyAssert(currentCount,testingCount);
       
      
       if(urlVal.isValid("http://255.255.255.255:80")){		//Valid range of ports
           currentCount++;
       }
       testingCount++;       
	   
	   
   }
   

   

    
   

   
   public void testManualTest()
   {
	   UrlValidator urlVal = new UrlValidator(null, null, UrlValidator.ALLOW_ALL_SCHEMES);
	   System.out.println("\nTesting URL SCHEME: \n");
	   System.out.println(urlVal.isValid("http://www.amazon.com")); //true
	   
	  
	   System.out.println(urlVal.isValid("ftp://www.amazon.com")); //true
	   System.out.println(urlVal.isValid("h3t://www.amazon.com")); //true
	   System.out.println(urlVal.isValid("http:/www.amazon.com")); //false
	   System.out.println(urlVal.isValid("http/www.amazon.com"));  //false
	   System.out.println(urlVal.isValid("://www.amazon.com")); //false
	   System.out.println(urlVal.isValid("www.amazon.com"));  //true ---BUG
	   
	   
	 //testing top level domians
	   System.out.println("\nTesting Top Level Domains: \n");
	   System.out.println(urlVal.isValid("http://www.amazon.com")); //True
	   System.out.println(urlVal.isValid("http://www.amazon.net"));  //true
	   System.out.println(urlVal.isValid("http://www.amazon.mil")); //true
	   System.out.println(urlVal.isValid("http://www.amazon.int")); //true
	   System.out.println(urlVal.isValid("http://www.amazon.org"));   //true
	   System.out.println(urlVal.isValid("http://www.amazon.gov")); //true
	   System.out.println(urlVal.isValid("http://www.amazon.edu")); //true
	   System.out.println(urlVal.isValid("http://www.amazon.foo")); //false
	   
	   //country codes
	   System.out.println("\nTesting Country Code Top Level Domains: \n");
	   System.out.println(urlVal.isValid("http://www.amazon.au")); //True
	   System.out.println(urlVal.isValid("http://www.amazon.ca"));  //true
	   System.out.println(urlVal.isValid("http://www.amazon.cn")); //true
	   System.out.println(urlVal.isValid("http://www.amazon.de")); //true
	   System.out.println(urlVal.isValid("http://www.amazon.uk"));   //true
	   System.out.println(urlVal.isValid("http://www.amazon.fr")); //true
	   System.out.println(urlVal.isValid("http://www.amazon.jp")); //true
	   System.out.println(urlVal.isValid("http://www.amazon.kr")); //true
	   System.out.println(urlVal.isValid("http://www.amazon.ru")); //true
	  
	   //testing lower and upper bounds of IP notation
	   System.out.println("\nTesting IP notation: \n");
	   System.out.println(urlVal.isValid("http://255.240.235.255")); //True
	   System.out.println(urlVal.isValid("http://255.256.257.258"));  //false
	   System.out.println(urlVal.isValid("http://0.0.0.0"));   //true
	   System.out.println(urlVal.isValid("http://-225.-102.-293.0")); //false
	  
	   //URL Authority
	   System.out.println("\n Testing URL Authority:\n");  //true
	   System.out.println(urlVal.isValid("www.go.com"));  //true
	   System.out.println(urlVal.isValid("www.gooogle.com"));
	   System.out.println(urlVal.isValid(""));
   }
   
   public void testInputPartitioning(String testUrl, boolean expectedOutput) {		//Function to speed up partition testing
		UrlValidator urlValidator = new UrlValidator();		//Make new urlvalidator object
		boolean testOutput = urlValidator.isValid(testUrl); //Call isValid function

		if (expectedOutput != testOutput) {					//The expected output should match the testOutput
			if (expectedOutput == true){
				System.out.println("Test failed, expected it to pass");		//If they don't match and the expected output was pass, inform user
			} else {
				System.out.println("Test passed, expected it to fail");		//Otherwise, tell user test passed when it should have failed
			}
		}
		else {
			System.out.println("No Issues");			//If everything is fine then don't print any issues
		}
}
   
   public void testYourFirstPartition()
   {
	   testInputPartitioning("http://www.google.com:500/a/b_c?d=50+me&e=hello#test_me", true);		//Valid URLs, these should be fine
       
       testInputPartitioning("http://www.google.com", true);		//We expect these to return true
       
       testInputPartitioning("http://www.google.com/x/y/z", true);

       testInputPartitioning("http://www.google.com:500", true);
       
       
       																									//The rest should raise issues if they pass isValis()
       testInputPartitioning("http://&&&:2000/a/b_c?d=50+me&e=hello#test_me", false); //Host is incorrect

       
       testInputPartitioning("htp://www.google.com:2000/a/b_c?d=50+me&e=hello#test_me", false);  //Scheme is incorrect


       
       testInputPartitioning("http://www.google.com:2000/;//b_c?d=50+me&e=hello#test_me", false);  //Path is incorrect
       
       
       testInputPartitioning("http://www.google.com:2000/a/b_c?d=50+me&e=hello#;;", false);  //Fragment is incorrect


       
       testInputPartitioning("http://www.google.com:port/a/b_c?d=50+me&e=hello#test_me", false); //Port is incorrect
   }
   
   public void testYourSecondPartition(){
	   
   }
   
   
   public void testIsValid()
   {
	   UrlValidator urlValidator = new UrlValidator();
	   int failCount = 0, passCount = 0, total =0;
	   Boolean scheme, auth, port, path, query, g, oG;
	   for(int i = 0;i<100;i++)
	   {
		   for (int j = 0; j < testUrlScheme.length; ++j)
		   {   	 
			   for (int k = 0; k < testUrlAuthority.length; ++k)
			   {
				   for (int l = 0; l < testUrlPort.length; ++l)
				   {
					   for (int m = 0; m < testPath.length; ++m)
					   {
						   for (int n = 0; n < testUrlQuery.length; ++n) {
							   
							   StringBuffer mikeBuffer = new StringBuffer();
							   mikeBuffer.append(testUrlScheme[j].item);
							   scheme = testUrlScheme[j].valid;			
							   mikeBuffer.append(testUrlAuthority[k].item);
							   auth = testUrlAuthority[k].valid;
							   mikeBuffer.append(testUrlPort[l].item);
							   port = testUrlPort[l].valid;					
							   mikeBuffer.append(testPath[m].item);
							   path = testPath[m].valid;							  
							   mikeBuffer.append(testUrlQuery[n].item);
							   query = testUrlQuery[n].valid;
							   String results = mikeBuffer.toString();
							   oG = urlValidator.isValid(results);						   
							   if(scheme && path && port && auth && query) {
								   g =true;
							   }
							   else {
								   g= false;
							   }
							   
							   if(oG != g) {
								   failCount++;
								   System.out.println("Test case failed on URL: " + results + " expected: "+ g+" actual results: " + oG);
							   }
							   else {
								   passCount++;
								   System.out.println("Test case Passed on URL: " + results + " expected: "+ g+" actual results: " + oG);
							   }
							   total++;
						   }
					   }
				   }
			   }
		   }
	   }
	   System.out.println("Out of "+ total +" tests, "+ passCount +" passed and " + failCount+" failed" );
   }
					   
   
   public void testAnyOtherUnitTest()
   {
	   
   }
   /**
    * Create set of tests by taking the testUrlXXX arrays and
    * running through all possible permutations of their combinations.
    *
    * @param testObjects Used to create a url.
    */
   ResultPair[] testUrlScheme = {new ResultPair("http://", true),
           new ResultPair("ftp://", true),
           new ResultPair("h3t://", true),
           new ResultPair("3ht://", false),
           new ResultPair("http:/", false),
           new ResultPair("http:", false),
           new ResultPair("http/", false),
           new ResultPair("://", false),
           new ResultPair("", true)};

ResultPair[] testUrlAuthority = {new ResultPair("www.google.com", true),
              new ResultPair("go.com", true),
              new ResultPair("go.au", true),
              new ResultPair("0.0.0.0", true),
              new ResultPair("255.255.255.255", true),
              new ResultPair("256.256.256.256", false),
              new ResultPair("255.com", true),
              new ResultPair("1.2.3.4.5", false),
              new ResultPair("1.2.3.4.", false),
              new ResultPair("1.2.3", false),
              new ResultPair(".1.2.3.4", false),
              new ResultPair("go.a", false),
              new ResultPair("go.a1a", false),
              new ResultPair("go.cc", true),
              new ResultPair("go.1aa", false),
              new ResultPair("aaa.", false),
              new ResultPair(".aaa", false),
              new ResultPair("aaa", false),
              new ResultPair("", false)
};
ResultPair[] testUrlPort = {new ResultPair(":80", true),
         new ResultPair(":65535", true),
         new ResultPair(":0", true),
         new ResultPair("", true),
         new ResultPair(":-1", false),
         new ResultPair(":65636", true),
         new ResultPair(":65a", false)
};
ResultPair[] testPath = {new ResultPair("/test1", true),
      new ResultPair("/t123", true),
      new ResultPair("/$23", true),
      new ResultPair("/..", false),
      new ResultPair("/../", false),
      new ResultPair("/test1/", true),
      new ResultPair("", true),
      new ResultPair("/test1/file", true),
      new ResultPair("/..//file", false),
      new ResultPair("/test1//file", false)
};
//Test allow2slash, noFragment
ResultPair[] testUrlPathOptions = {new ResultPair("/test1", true),
                new ResultPair("/t123", true),
                new ResultPair("/$23", true),
                new ResultPair("/..", false),
                new ResultPair("/../", false),
                new ResultPair("/test1/", true),
                new ResultPair("/#", false),
                new ResultPair("", true),
                new ResultPair("/test1/file", true),
                new ResultPair("/t123/file", true),
                new ResultPair("/$23/file", true),
                new ResultPair("/../file", false),
                new ResultPair("/..//file", false),
                new ResultPair("/test1//file", true),
                new ResultPair("/#/file", false)
};

ResultPair[] testUrlQuery = {new ResultPair("?action=view", true),
          new ResultPair("?action=edit&mode=up", true),
          new ResultPair("", true)
};

Object[] testUrlParts = {testUrlScheme, testUrlAuthority, testUrlPort, testPath, testUrlQuery};
Object[] testUrlPartsOptions = {testUrlScheme, testUrlAuthority, testUrlPort, testUrlPathOptions, testUrlQuery};
int[] testPartsIndex = {0, 0, 0, 0, 0};

//---------------- Test data for individual url parts ----------------
ResultPair[] testScheme = {new ResultPair("http", true),
        new ResultPair("ftp", false),
        new ResultPair("httpd", false),
        new ResultPair("telnet", false)};

}