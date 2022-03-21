const static auto PROG1 =
    R"(func test(x){
  i = 25
  if x <= 0 then
    x = x + 2.5
  else
    x = x - 2.7
  return x
}

func main(args){
  i = 0
  while(i == 0){
    func(35)
  }
}
)";