// This autogenerated skeleton file illustrates how to build a server.
// You should copy it to another filename to avoid overwriting it.

#include "gen-cpp/Calculator.h"

#include <thrift/protocol/TBinaryProtocol.h>
#include <thrift/transport/TSocket.h>
#include <thrift/transport/TTransportUtils.h>
#include <iostream>

using namespace apache::thrift;
using namespace apache::thrift::protocol;
using namespace apache::thrift::transport;

using namespace boost;

int main(int argc, char **argv) {
  shared_ptr<TTransport> socket(new TSocket("localhost", 9999));
  shared_ptr<TTransport> transport(new TBufferedTransport(socket));
  shared_ptr<TProtocol> protocol(new TBinaryProtocol(transport));
  CalculatorClient calc(protocol);

  transport->open();

  // We calculate the following expression.  The variable names correspond to the operator they
  // appear under here:
  // ((5 * 2) + ((7 - 3) * 10)) / (6 - 4)
  //     a    e     b    d      f    c
  // The result should be 25.

  std::cout << "starting requests..." << std::endl;

  // Thift's approach to async is weird.  You have to order your sends and recvs...

  calc.send_sub(7, 3);   // b
  calc.send_mult(5, 2);  // a
  calc.send_sub(6, 4);   // c
  calc.send_mult(calc.recv_sub(), 10);  // d
  int a = calc.recv_mult();
  int c = calc.recv_sub();
  calc.send_add(a, calc.recv_mult());  // e
  int f = calc.div(calc.recv_add(), c);  // f

  std::cout << "result = " << f << std::endl;

  return 0;
}
